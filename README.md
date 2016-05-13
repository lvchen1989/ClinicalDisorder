A deep learning framework for clinical disorder recognition
======
ClinicalDisorder is a package for Clinical Disorder Recognition using recurrent neural networks based on package LibN3L. 

System configuration
======
* Download the [LibN3L](https://github.com/SUTDNLP/LibN3L) library and configure your system. Please refer to [Here](https://github.com/SUTDNLP/LibN3L). This is a deep learning toolkit in C++, designed specially for NLP. It includes different ***Neural network architectures*** (TNN, RNN, GatedNN, LSTM and GRNN) with ***Objective function***(sigmoid, CRF max-margin, CRF maximum likelihood). In addition, this package can easily support various user-defined neural network structures.
* Note that we have changed MyLib.h and Metric.h in this package for our task. Please use the package released in our project and follow the instructions on [LibN3L](https://github.com/SUTDNLP/LibN3L) and configure your system.
* Open [LSTMRNN/CMakeLists.txt](CMakeLists.txt) and change " ../LibN3L/" into the directory of your [LibN3L](https://github.com/SUTDNLP/LibN3L) package.
* Run the [demo-entity.sh](demo-entity.sh) file: `sh demo-entity.sh`

Compile
======
cmake .
make LSTMNoCharCRFMMLabeler

***LSTMNoCharCRFMMLabeler*** is the bidirectional LSTM.

Train
=====
This is an training example.

./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune50 -word ../embedding/bio/semeval.50.vec1 -model example/demoLSTMMM50.model

-l: training
-train: train set.
-test: test set. In this training command, it is used to construct the word embedding vocabulary.
-option:  parameter setting file
-word: pretrained word embedding
-model: the path of saved model file


The demo system includes clinical disorder recognition sample data(["trainsample.txt"](LSTMRNN/data/trainsample.txt), and ["trainsample.txt"](LSTMRNN/data/testsample.txt), English word embeding sample file(["sena.emb"](embeddings/senna/sena.emb) and parameter setting file(["option.tune"](LSTMRNN/example/optiontune). All of these files are gathered at folder [NNNamedEntity/example](example).
 
This demo system runs a ***SparseTNNCRFMLLabeler*** model which means a traditional neural network with sparse feature and use CRF maximun likelihood as the objective function. 

The demo system will generate three files: "Entity.devOUTdemo", "demo.model" and "Entity.test.output" at [NNNamedEntity/example](example). "Entity.devOUTdemo" is the tagged dev file during training process. "demo.model" is the best predicting model in all training process. "Entity.test.output" is the final tagged result for ["Entity.test"](example/Entity.test) in tagger process based on the generated model "demo.model".

Note: 
======
* Current version only compatible with [LibN3L](https://github.com/SUTDNLP/LibN3L) after ***Dec. 10th 2015*** , which contains the model saving and loading module.
* The example files are just to verify the running for the code. For copyright consideration, we take only hundreds of sentences as example. Hence the results on those example datasets does not represent the real performance on large dataset.
* The .cpp file also provide gradient checking for verify your code, it is commentted out by defult. It is necessary to set "dropout = 0" in [demo.option](example/demo.option) before you enable the gradient checking.


Monitoring information
=====
During the running of this NER system, it may print out the follow log information:


The first "Recall..." line shows the performance of the dev set and the second "Recall..." line shows 
you the performance of the test set.


Updating...
====
* 2015-12-02: support model saving and loading.
* 2015-12-11: fix test() output file bug. Previous version's output is golden test file, this version sets the output to be the predicted file.
* 2016-01-15: fix init() with setwordembeddingfinetune bug.

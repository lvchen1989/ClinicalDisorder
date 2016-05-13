A deep learning framework for clinical disorder recognition
======
ClinicalDisorder is a package for Clinical Disorder Recognition using recurrent neural networks based on package LibN3L. 

System configuration
======
* Download the [LibN3L](https://github.com/SUTDNLP/LibN3L) library and configure your system. Please refer to [Here](https://github.com/SUTDNLP/LibN3L). This is a deep learning toolkit in C++, designed specially for NLP. It includes different ***Neural network architectures*** (TNN, RNN, GatedNN, LSTM and GRNN) with ***Objective function***(sigmoid, CRF max-margin, CRF maximum likelihood). In addition, this package can easily support various user-defined neural network structures.
* Note that we have changed MyLib.h and Metric.h in this package for our task. Please use the package released in our project and follow the instructions on [LibN3L](https://github.com/SUTDNLP/LibN3L) and configure your system.
* Open [LSTMRNN/CMakeLists.txt](CMakeLists.txt) and change " ../LibN3L/" into the directory of your [LibN3L](https://github.com/SUTDNLP/LibN3L) package.

Compile
======
* cmake .
* make LSTMNoCharCRFMMLabeler

***LSTMNoCharCRFMMLabeler*** is the bidirectional LSTM.

Training
=====
This is a training example.

* ./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune50 -word ../embedding/bio/semeval.50.vec1 -model example/demoLSTMMM50.model

-l: training. 

-train: train set. 

-test: test set. In this training command, it is only used for constructing the word embedding vocabulary. 

-option:  parameter setting file. 

-word: pretrained word embedding. 

-model: the path of saved model file. 



The demo system includes clinical disorder recognition sample data(["trainsample.txt"](LSTMRNN/data/trainsample.txt), and ["testsample.txt"](LSTMRNN/data/testsample.txt)), English word embeding sample file(["sena.emb"](embeddings/senna/sena.emb)) and parameter setting file(["option.tune"](LSTMRNN/example/optiontune)). All of these files are in the path described in the above trainning command.
 
This demo system runs a ***LSTMNoCharCRFMMLabeler*** model which means a bidirectional LSTM neural network and use CRF maximun margin as the objective function. 

The demo system will generate model file: "demoLSTMMM50.model" at [LSTMRNN/example](example).

Test:
=====

This is a test example.

* ./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMM50.model -output data/testLSTMMM50.output

-test: test set.

-model: the model used for testing.

-outoput: the predicted result fot the test file (["testsample.txt"](LSTMRNN/data/testsample.txt)) based on the model "demoLSTMMM50.model".

Demo system:
=====
* Run the [neuralLSTMMMNoC-50vec.sh](LSTMRNN/neuralLSTMMMNoC-50vec.sh) file: `sh neuralLSTMMMNoC-50vec.sh`. This is a simple integration of the above process.
* You can run `sh cleanall.sh` to clean the files generated by the source.

Note: 
======
* Current version only compatible with [LibN3L](https://github.com/SUTDNLP/LibN3L) after ***Dec. 10th 2015*** , which contains the model saving and loading module.
* The example files are just to verify the running for the code. For copyright consideration, we take only some sentences as example. Hence the results on those example datasets does not represent the real performance on large dataset.
* The corpus used for ShARe/CLEF eHealth 2013 challenge consists of annotations over de-identied clinical reports from a US intensive care department (version 2.5 of the MIMIC II database)(http://mimic.physionet.org). We can access the data set following the instruction on the website of the challenge (https://sites.google.com/site/shareclefehealth/data).
* The .cpp file also provide gradient checking for verify your code, it is commentted out by defult. It is necessary to set "dropout = 0" in ["option.tune"](LSTMRNN/example/optiontune) before you enable the gradient checking.


Monitoring information
=====
During the running of this NER system, it may print out the follow log information:


The first "Recall..." line shows the performance of the dev set and the second "Recall..." line shows 
you the performance of the test set.


Updating...
====

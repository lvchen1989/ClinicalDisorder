cmake .
make LSTMUnNoCharCRFMMLabeler
./LSTMUnNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tunesenna -word ../embedding/senna/sena.emb -model example/demoLSTMUnMMsenna.model
./LSTMUnNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMUnMMsenna.model -output data/testLSTMUnMMsenna.output

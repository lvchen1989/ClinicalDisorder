cmake .
make LSTMUnNoCharCRFMMLabeler
./LSTMUnNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune50 -word ../embedding/bio/semeval.50.vec1 -model example/demoLSTMUnMM50.model
./LSTMUnNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMUnMM50.model -output data/testLSTMUnMM50.output

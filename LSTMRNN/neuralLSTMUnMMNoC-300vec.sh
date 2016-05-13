cmake .
make LSTMUnNoCharCRFMMLabeler
./LSTMUnNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune -word ../embedding/bio/semeval.300.vec1 -model example/demoLSTMUnMM300.model
./LSTMUnNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMUnMM300.model -output data/testLSTMUnMM300.output

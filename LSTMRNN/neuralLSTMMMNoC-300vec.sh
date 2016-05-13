cmake .
make LSTMNoCharCRFMMLabeler
./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune -word ../embedding/bio/semeval.300.vec1 -model example/demoLSTMMM300.model
./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMM300.model -output data/testLSTMMM300.output

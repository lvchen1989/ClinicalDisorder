cmake .
make LSTMNoCharCRFMMLabeler
./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune50 -word ../embedding/bio/semeval.50.vec1 -model example/demoLSTMMM50.model
./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMM50.model -output data/testLSTMMM50.output

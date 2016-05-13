cmake .
make LSTMUnNoCharCRFMMLabeler
./LSTMUnNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txtt -option example/option.tuneran -model example/demoLSTMUnMMran300.model
./LSTMUnNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMUnMMran300.model -output data/testLSTMUnMMran300.output

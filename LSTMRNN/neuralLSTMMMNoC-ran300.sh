cmake .
make LSTMNoCharCRFMMLabeler
./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tuneran -model example/demoLSTMMMran300.model
./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMMran300.model -output data/testLSTMMMran300.output

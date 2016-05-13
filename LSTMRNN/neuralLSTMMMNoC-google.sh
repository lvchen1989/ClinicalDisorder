cmake .
make LSTMNoCharCRFMMLabeler
./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune -word ../embedding/senna/google.txt -model example/demoLSTMMMgoogle.model
./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMMgoogle.model -output data/testLSTMMMgoogle.output

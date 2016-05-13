cmake .
make LSTMUnNoCharCRFMMLabeler
./LSTMUnNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tune -word ../embedding/senna/google.txt -model example/demoLSTMUnMMgoogle.model
./LSTMUnNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMUnMMgoogle.model -output data/testLSTMUnMMgoogle.output

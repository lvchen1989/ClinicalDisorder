cmake .
make LSTMNoCharCRFMMLabeler
./LSTMNoCharCRFMMLabeler -l -train data/trainsample.txt -test data/testsample.txt -option example/option.tunesenna -word ../embedding/senna/sena.emb -model example/demoLSTMMMsenna.model
./LSTMNoCharCRFMMLabeler -test data/testsample.txt -model example/demoLSTMMMsenna.model -output data/testLSTMMMsenna.output

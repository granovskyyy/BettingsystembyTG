CC=g++
CFLAGS = -Wall -g
SRCS = auth.cpp app.cpp main.cpp userprofile.cpp wallet.cpp 
TARGET=betplanet
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)
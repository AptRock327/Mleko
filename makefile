.PHONY: clean

mleko: $(wildcard src/*.c)
	gcc -Iinclude -o $@ $^
	
clean:
	rm mleko

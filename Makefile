CC='g++'
SRC_DIR=./src
all: aging_register clock stack counter

aging_register: $(SRC_DIR)/aging_register.cpp
	$(CC) $(SRC_DIR)/aging_register.cpp -o aging_register

clock: $(SRC_DIR)/clock.cpp
	$(CC) $(SRC_DIR)/clock.cpp -o clock

stack: $(SRC_DIR)/stack.cpp
	$(CC) $(SRC_DIR)/stack.cpp -o stack

counter: $(SRC_DIR)/counter.cpp
	$(CC) $(SRC_DIR)/counter.cpp -o counter


clean:
	@if test -n "$(wildcard aging_register)"; then \
		rm aging_register; \
		echo 'removed aging_register'; \
	fi
	@if test -n "$(wildcard clock)"; then \
		rm clock; \
		echo 'removed clock'; \
	fi
	@if test -n "$(wildcard stack)"; then \
		rm stack; \
		echo 'removed stack'; \
	fi
	@if test -n "$(wildcard counter)"; then \
		rm counter; \
		echo 'removed counter'; \
	fi

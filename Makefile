CC='g++'

all: aging_register second_chance stack counter

aging_register: aging_register.cpp
	$(CC) aging_register.cpp -o aging_register

second_chance: second_chance.cpp
	$(CC) second_chance.cpp -o second_chance

stack: stack.cpp
	$(CC) stack.cpp -o stack

counter: counter.cpp
	$(CC) counter.cpp -o counter


clean:
	@if test -n "$(wildcard aging_register)"; then \
		rm aging_register; \
		echo 'removed aging_register'; \
	fi
	@if test -n "$(wildcard second_chance)"; then \
		rm second_chance; \
		echo 'removed second_chance'; \
	fi
	@if test -n "$(wildcard stack)"; then \
		rm stack; \
		echo 'removed stack'; \
	fi
	@if test -n "$(wildcard counter)"; then \
		rm counter; \
		echo 'removed counter'; \
	fi

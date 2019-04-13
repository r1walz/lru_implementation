CC='g++'

all: aging_register clock stack counter

aging_register: aging_register.cpp
	$(CC) aging_register.cpp -o aging_register

clock: clock.cpp
	$(CC) clock.cpp -o clock

stack: stack.cpp
	$(CC) stack.cpp -o stack

counter: counter.cpp
	$(CC) counter.cpp -o counter


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

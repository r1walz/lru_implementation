CC='g++'
SRCDIR=./src

all: aging_register clock stack counter

aging_register: $(SRCDIR)/aging_register.cpp
	$(CC) $(SRCDIR)/aging_register.cpp -o aging_register

clock: $(SRCDIR)/clock.cpp
	$(CC) $(SRCDIR)/clock.cpp -o clock

stack: $(SRCDIR)/stack.cpp
	$(CC) $(SRCDIR)/stack.cpp -o stack

counter: $(SRCDIR)/counter.cpp
	$(CC) $(SRCDIR)/counter.cpp -o counter


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

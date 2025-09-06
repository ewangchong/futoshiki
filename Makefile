# Top-level Makefile for Futoshiki Project

.PHONY: all run-c run-cpp run-py clean

all:
	$(MAKE) -C c
	$(MAKE) -C cpp

run-c:
	$(MAKE) -C c run

run-cpp:
	$(MAKE) -C cpp run-cpp

run-py:
	python3 python/futoshiki.py

clean:
	$(MAKE) -C c clean
	$(MAKE) -C cpp clean

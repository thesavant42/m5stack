.PHONY: dev
dev:
	mcconfig -d -m

.PHONY: build
build:
	cd ${IDF_PATH} && \
	./install.sh && \
	source ${IDF_PATH}/export.sh && \
	cd - && \
	mcconfig -d -m -p esp32/m5stack_cores3

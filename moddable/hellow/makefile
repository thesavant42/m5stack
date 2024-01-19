.PHONY: xsbug
xsbug:
	open ${MODDABLE}/build/bin/mac/release/xsbug.app

.PHONY: build
build:
	cd ${IDF_PATH} && \
	./install.sh && \
	source ${IDF_PATH}/export.sh && \
	cd ~/Work/m5stack/moddable/hellow/ && \
	mcconfig -d -m -p esp32/m5stack_cores3

all: subsystems

subsystems:
	cd Chapter01 && $(MAKE)
	cd Chapter02 && $(MAKE)
	cd Chapter03 && $(MAKE)
	cd Chapter05 && $(MAKE)
	cd Chapter06 && $(MAKE)
	cd Chapter07 && $(MAKE)
	cd Chapter08 && $(MAKE)
	cd Chapter09 && $(MAKE)
	cd Chapter10 && $(MAKE)
	cd Chapter12 && $(MAKE)
	cd Chapter14 && $(MAKE)
	cd Chapter15 && $(MAKE)
	cd Chapter17 && $(MAKE)
	cd Chapter18 && $(MAKE)

clean:
	@cd Chapter01 && $(MAKE) clean
	@cd Chapter02 && $(MAKE) clean
	@cd Chapter03 && $(MAKE) clean
	@cd Chapter05 && $(MAKE) clean
	@cd Chapter06 && $(MAKE) clean
	@cd Chapter07 && $(MAKE) clean
	@cd Chapter08 && $(MAKE) clean
	@cd Chapter09 && $(MAKE) clean
	@cd Chapter10 && $(MAKE) clean
	@cd Chapter12 && $(MAKE) clean
	@cd Chapter14 && $(MAKE) clean
	@cd Chapter15 && $(MAKE) clean
	@cd Chapter17 && $(MAKE) clean
	@cd Chapter18 && $(MAKE) clean
	
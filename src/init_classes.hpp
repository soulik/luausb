namespace luausb {
	void initConstants(State * state, Module & module);
	void initContext(State * state, Module & module);
	void initDevice(State * state, Module & module);
	void initDeviceHandle(State * state, Module & module);
	void initInterface(State * state, Module & module);
	void initTransfer(State * state, Module & module);

	void initBosDescriptor(State * state, Module & module);
	void initBosDevCapabilityDescriptor(State * state, Module & module);
	void initConfigDescriptor(State * state, Module & module);
	void initContainerIDDescriptor(State * state, Module & module);
	void initControlSetup(State * state, Module & module);
	void initDeviceDescriptor(State * state, Module & module);
	void initEndpointDescriptor(State * state, Module & module);
	void initInterfaceDescriptor(State * state, Module & module);
	void initISOPacketDescriptor(State * state, Module & module);
	void initUSB20ExtensionDescriptor(State * state, Module & module);
	void initSSUSBDeviceCapabilityDescriptor(State * state, Module & module);
	void initSSEndpointCompanionDescriptor(State * state, Module & module);
};

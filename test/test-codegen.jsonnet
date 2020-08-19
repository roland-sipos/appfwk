local ccm = import "ccm.jsonnet";
local schemalist = [
    import "fake-schema.jsonnet",
];
ccm.codegen("Test", "dunedaq::appfwk", schemalist)

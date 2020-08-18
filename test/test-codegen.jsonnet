local ccm = import "ccm.jsonnet";
local schemalist = [
    import "fake-schema.jsonnet",
];
ccm.codegen("test", "dunedaq::appfwk::test", schemalist)

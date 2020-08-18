local ccm = import "ccm.jsonnet";
local schemalist = [
    import "ccm-schema.jsonnet",
];
ccm.codegen("ccm", "dunedaq::appfwk::ccm", schemalist)

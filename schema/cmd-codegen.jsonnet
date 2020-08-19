local ccm = import "ccm.jsonnet";
local schemalist = [
    import "cmd-schema.jsonnet",
];
ccm.codegen("Cmd", "dunedaq::appfwk::cmd", schemalist)

// Schema for the Fake* modules
local ccmschema = import "ccm-schema.jsonnet";
function(schema) {

    ccm: ccmschema(schema),

    fakedpc_fields(inout):: [
        schema.field(inout, $.ccm.ident,
                     doc="Name of %s queue"%inout),
        schema.field("nIntsPerVector_", $.ccm.int, 10,
                     doc="Number of values per vector"),
        schema.field("starting_int", $.ccm.int, -4,
                     doc="Initial value"),
        schema.field("ending_int", $.ccm.int, 14,
                     doc="Ending value"),
        schema.field("queue_timeout_ms", $.ccm.int, 1000,
                     doc="Dlay in ms to wait for queue")],

    fdp: schema.record("FakeDataProducerCfg",
                       fields=$.fakedpc_fields("output") + [
                           schema.field("wait_between_sends_ms", $.ccm.int, 1000,
                                        doc="Delay in ms between sends")
                       ], doc="Configuration for FakeDataProducerDAQMOdule"),

    fdc: schema.record("FakeDataConsumerCfg", fields=$.fakedpc_fields("input"),
                       doc="Configuration for FakeDataConsumerDAQMOdule"),

    types: [$.ccm.ident, $.ccm.int, $.fdp, $.fdc]

}

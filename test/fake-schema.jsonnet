// Schema for commands to the Fake* modules
local cmdschema = import "cmd-schema.jsonnet";
function(schema) {

    cs: cmdschema(schema),

    fakedpc_fields(inout):: [
        schema.field(inout, $.cs.ident,
                     doc="Name of %s queue"%inout),
        schema.field("starting_int", $.cs.int, -4,
                     doc="Initial value"),
        schema.field("ending_int", $.cs.int, 14,
                     doc="Ending value"),
        // FIXME: original C++ uses std::chrono::milliseconds not generic int.
        // To support this we can add a new type code (ie, like "i4").
        schema.field("queue_timeout_ms", $.cs.int, 1000,
                     doc="Dlay in ms to wait for queue")],

    fdp: schema.record("FakeDataProducerCfg",
                       fields=$.fakedpc_fields("output") + [
                           schema.field("wait_between_sends_ms", $.cs.int, 1000,
                                        doc="Delay in ms between sends"),
                           schema.field("nIntsPerVector", $.cs.ulong, 10,
                                        doc="Number of values per vector"),
                       ], doc="Configuration for FakeDataProducerDAQMOdule"),

    fdc: schema.record("FakeDataConsumerCfg", fields=$.fakedpc_fields("input"),
                       doc="Configuration for FakeDataConsumerDAQMOdule"),

    types: [$.cs.ident, $.cs.int, $.fdp, $.fdc]

}

# 2025-09-23T14:46:17.445630
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "PF_SoC_EV_test",hw_design = "$COMPONENT_LOCATION/../../verilog/SoC_EV_prj/SoC_EV_bd_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",generate_dtb = False,advanced_options = advanced_options,compiler = "gcc")

comp = client.create_app_component(name="HW_SoC_EV_test",platform = "$COMPONENT_LOCATION/../PF_SoC_EV_test/export/PF_SoC_EV_test/PF_SoC_EV_test.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="PF_SoC_EV_test")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_test")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

vitis.dispose()


# 2025-09-25T11:02:23.006499
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "PF_SoC_EV_test2",hw_design = "$COMPONENT_LOCATION/../../../SoC_EV_IPmodule/SoC_EV_BD_wrapper.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",generate_dtb = False,advanced_options = advanced_options,compiler = "gcc")

comp = client.create_app_component(name="HW_SoC_EV_test2",platform = "$COMPONENT_LOCATION/../PF_SoC_EV_test2/export/PF_SoC_EV_test2/PF_SoC_EV_test2.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="PF_SoC_EV_test2")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_test2")
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

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "PF_SoC_EV_test3",hw_design = "$COMPONENT_LOCATION/../../../SoC_EV_IPmodule/SoC_EV_BD_wrapper2.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",generate_dtb = False,advanced_options = advanced_options,compiler = "gcc")

comp = client.create_app_component(name="HW_SoC_EV_test3",platform = "$COMPONENT_LOCATION/../PF_SoC_EV_test3/export/PF_SoC_EV_test3/PF_SoC_EV_test3.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="PF_SoC_EV_test3")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_test3")
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

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "PF_SoC_EV_test4",hw_design = "$COMPONENT_LOCATION/../../../SoC_EV_IPmodule/SoC_EV_BD_wrapper3.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",generate_dtb = False,advanced_options = advanced_options,compiler = "gcc")

comp = client.create_app_component(name="HW_SoC_EV_test4",platform = "$COMPONENT_LOCATION/../PF_SoC_EV_test4/export/PF_SoC_EV_test4/PF_SoC_EV_test4.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="PF_SoC_EV_test4")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_test4")
comp.build()

status = platform.build()

comp.build()


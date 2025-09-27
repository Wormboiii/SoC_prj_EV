# 2025-09-27T12:32:43.432072
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "PF_SoC_EV_Final",hw_design = "$COMPONENT_LOCATION/../../../SoC_EV_IPmodule/SoC_EV_BD_wrapper_final.xsa",os = "standalone",cpu = "microblaze_riscv_0",domain_name = "standalone_microblaze_riscv_0",generate_dtb = False,advanced_options = advanced_options,compiler = "gcc")

comp = client.create_app_component(name="HW_SoC_EV_Final",platform = "$COMPONENT_LOCATION/../PF_SoC_EV_Final/export/PF_SoC_EV_Final/PF_SoC_EV_Final.xpfm",domain = "standalone_microblaze_riscv_0",template = "hello_world")

platform = client.get_component(name="PF_SoC_EV_Final")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_Final")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()


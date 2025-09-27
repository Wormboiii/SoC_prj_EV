# 2025-09-27T12:36:50.234365
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

platform = client.get_component(name="PF_SoC_EV_Final")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_Final")
comp.build()

client.delete_component(name="HW_SoC_EV_test3")

client.delete_component(name="HW_SoC_EV_test2")

client.delete_component(name="HW_SoC_EV_test")

client.delete_component(name="PF_SoC_EV_test")

client.delete_component(name="PF_SoC_EV_test2")

client.delete_component(name="PF_SoC_EV_test3")

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


# 2025-09-26T16:04:33.689732
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

platform = client.get_component(name="PF_SoC_EV_test4")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_test4")
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


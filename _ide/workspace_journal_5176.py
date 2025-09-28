# 2025-09-28T12:35:36.503221
import vitis

client = vitis.create_client()
client.set_workspace(path="Vitis_prj")

platform = client.get_component(name="PF_SoC_EV_Final")
status = platform.build()

comp = client.get_component(name="HW_SoC_EV_Final")
comp.build()

status = platform.build()

comp.build()

vitis.dispose()


# SM-GetMem
Get memory usage of current running SrCDS server.

Requires SourceMod.


Most of this code from Kxnrl#0001, in the AlliedModders discord, here: https://canary.discord.com/channels/335290997317697536/335290997317697536/856238249457614858 .


# Usage
Native provided as `Native int GetMem()`, returning mem usage in KB. With the plugin provided, use `sm_getmem`.

# TODOs
- Get HW mem (VmHWM)
- Clean up parseLine

# SM-GetMem
Get memory usage of current running SrCDS server.

Requires SourceMod.


~~Most of this code from Kxnrl#0001, in the AlliedModders discord, here: https://canary.discord.com/channels/335290997317697536/335290997317697536/856238249457614858 .~~

This extension has been wholly refactored, thanks to krxnl for giving me a good starting point.


# Usage
Native provided as `Native int GetMem()`, returning mem usage in KB. With the plugin provided, use `sm_getmem`.
`sm_cleanmem` - Run some memory cleaning commands (I recommend putting this in a server config / running it on map change)
`sm_getmem` && `sm_getmem_mb` - Get current used mem of running server

number=553
map = { --start of map
  version = "1.1",

  layers = { --end of layers

	    { --start of layers->0
	      type = "objectgroup",
	      name = "Object Layer 1",
	      visible = true,
	      opacity = 1,
	      properties = {},
	      objects ={
			{ 
			  name = "",
			  type = "lua_object",
			  x = 5,
			  y = 3,
			  width = 0,
			  height = 0,
			  gid = 12,
			  properties = {["script"]="object.lua"}
			},

			{ 
			  name = "",
			  type = "lua_object",
			  x = 7,
			  y = 6,
			  width = 0,
			  height = 0,
			  gid = 12,
			  properties = {["script"]="object2.lua"}
			}
	      } --end of layers->0
    	} --end of layers
} --start of layers
} --end of map

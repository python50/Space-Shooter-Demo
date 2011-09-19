--
--tile object implimented in lua
--

function init ( x, y)--, z, image_name, blank)
	
	return x;--{x, y, z, image_name, blank};
end

function update(x, y, z, image, delete)
	x+=1;

	if x > 30 or x < 0 then
		x=0;
	end
	
	return {x,y,z,image,delete};
end

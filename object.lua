--
--tile object implimented in lua
--

--- Must have these varibles
x=0;
y=0;
z=0;
image_name="ship1";
delete_this=0;
persistant=0;
no_collide=1;
id_type="lua_tile";

--- Other varibles
counter=0;

function init ()--, z, image_name, blank)

end

-- 2 | 1 
-- -- --
-- 3 | 0

function move( dir, speed )
	if     dir==0 then
		x=x+speed;
	elseif dir==1 then
		y=y-speed;
	elseif dir==2 then
		x=x-speed;
	elseif dir==3 then
		y=y+speed;
	end
end

function update()
	counter=counter+1;
	
	if (counter >= 0 and counter < 30) then
		move(0,3);
	elseif (counter >= 30 and counter < 60) then
		move(3,3);
	elseif (counter >= 60 and counter < 90) then
		counter=0;	
	end

	if (x < 0) then
		x=320; --C function map_width()
	end
	if (y < 0) then
		x=240; --C function map_height()
	end
	if (x > 320) then
		x=0; --C function map_width()
	end
	if (y > 240) then
		y=0; --C function map_height()
	end
end

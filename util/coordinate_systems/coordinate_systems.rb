# Generate conversion tables

require 'pp'

tau = 6.28318530718

def coordAsByteArray( x, y )
  "{#{(x*11.5+127.5).to_i},#{(y*11.5+127.5).to_i}}"
end

def printcoord( x, y )
  puts "#{x}\t#{y}"
end

# first, we compute the actual coordinates in a cartesian X, Y coordinates with distance 1 between neighboring LEDs, with LED #0 in 0, 0
# all computations later will follow the same sin/cos computations to locate pixels and retrieve the nearest (because of floats)
coords = []
coords << [0,0]
(1..11).each do |r|
  (0..5).each do |triangle|
    x = Math::cos( ( 4 + triangle ) * tau / 6.0 ) * r
    y = Math::sin( ( 4 + triangle ) * tau / 6.0 ) * r
    if( r == 11 ) # OOPS! bug in layout of the LEDs in physical layout of actual HEXXX machine, fuck, HACK IT in software!
      x += Math::cos( triangle * tau / 6.0 )
      y += Math::sin( triangle * tau / 6.0 )
    end
    coords << [x, y]
    (1..r-1).each do |i|
      x += Math::cos( triangle * tau / 6.0 )
      y += Math::sin( triangle * tau / 6.0 )
      coords << [x, y]
    end
  end
end

# helper method to find the nearest coordinate to a computed one
def findnearest( coords, targetx, targety )
  # find nearest coordinate
  nearest = 0
  targetcounter = 0
  target = -1
  coords.each do |neighborx,neighbory|
    d = Math::sqrt( ( neighborx - targetx ) ** 2 + ( neighbory - targety ) ** 2 )
    if d < 0.2
      target = targetcounter
    end
    targetcounter += 1
  end
  return target
end

# POSITION ARRAY
result = []
coords.each do |x,y|
  result << coordAsByteArray( x, y )
end
puts "int coordinates_array[297][2] = { #{result.join(", ")} };"
puts

# NEIGHBORS

#   2   1
#    \ /
# 3 - . - 0
#    / \
#   4   5

# go left
neighbors = []
(0..5).each do |direction|
  origincounter = 0
  coords.each do |pointx,pointy|
    targetx = pointx + 0.9 * Math::cos( direction * tau / 6.0 )
    targety = pointy + 0.9 * Math::sin( direction * tau / 6.0 )

    target = findnearest( coords, targetx, targety )
  
    if target == -1
      target = origincounter 
    end
#    puts "#{pointx}\t#{pointy}\t#{coords[targetcoord][0]}\t#{coords[targetcoord][1]}" # gnuplot check
    
    if direction == 0
      neighbors << [target]
    else
      neighbors[ origincounter ] << target
    end
  
    origincounter += 1
  end
end

neighborsAsStrings = []
neighbors.each do |ns|
  neighborsAsStrings << "{" + ns.join(",") + "}"
end

puts "int neighbors_array[297][6] = { #{neighborsAsStrings.join(", ")} };"
puts

# WARPING NEIGHBORS

# same as above, but when you hit an edge, you warp around to the other side
# because of the hexagon shape, this can't be wrapped donut-style like a square, but needs a bit of a "twist"

# go left
neighbors = []
(0..5).each do |direction|
  origincounter = 0
  coords.each do |pointx,pointy|
    targetx = pointx + 0.9 * Math::cos( direction * tau / 6.0 )
    targety = pointy + 0.9 * Math::sin( direction * tau / 6.0 )

    target = findnearest( coords, targetx, targety )
  
    if target == -1
      target = 331 + ( ( origincounter - 331 ) + 33 ) % 66; # rotate
    end
    
    if direction == 0
      neighbors << [target]
    else
      neighbors[ origincounter ] << target
    end
  
    origincounter += 1
  end
end

neighborsAsStrings = []
neighbors.each do |ns|
  neighborsAsStrings << "{" + ns.join(",") + "}"
end

puts "int warping_neighbors_array[297][6] = { #{neighborsAsStrings.join(", ")} };"
puts

# HEXXX IN A SKEWED AXIS COORDINATE SYSTEM

#                  Y
#                 /
#      -11,11    /
#         .-----/0,11
#        /     / \
# ______/_____/___\________ X
#  -11,0\    /0,0 /11,0
#        \  /    /
#         \/____/
#    0,-11/     11,-11
#        /

originx = 0
originy = 0
skewed2led_rows = []
led2skewed = {}
(-11..11).each do |x|
  skewed2led_row = []
  (-11..11).each do |y|
    targetx = originx + x * Math::cos( 0 * tau / 6.0 )
    targety = originy + x * Math::sin( 0 * tau / 6.0 )
    
    targetx = targetx + y * Math::cos( 1 * tau / 6.0 )
    targety = targety + y * Math::sin( 1 * tau / 6.0 )
    
    target = findnearest( coords, targetx, targety )
    
    if target != -1
      led2skewed[ target ] = [x,y]
    end
    skewed2led_row << "#{target}"
    
  end
  skewed2led_rows << skewed2led_row.join( ", " )
end

puts "int skewed2led_array[23][23] = { \n  { #{skewed2led_rows.join("}, \n  {")}}\n};"
puts

led2skewed_strings = []
led2skewed.sort.map do |key,value|
  led2skewed_strings << "{ #{value[0]}, #{value[1]} }"
end
puts "int led2skewed_array[397][2] = { #{led2skewed_strings.join( ", ")} };"
puts

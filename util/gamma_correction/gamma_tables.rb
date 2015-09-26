gamma = 2.8 # gamma of neopixels

corrected = []
inverted = []

(0..255).each do |i|
  vin = i / 255.0
  corrected << vout = ( 255 * vin ** (gamma) ).to_i
  inverted << vout = ( 255 * vin ** (1/gamma) ).to_i
end

puts "uint8_t gammaCorrection[ 256 ] = { #{corrected.join( ", " )} };"
puts "uint8_t gammaError[ 256 ] = { #{inverted.join( ", " )} };"

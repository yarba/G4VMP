# Use the magic that is @art_make@ to construct the shared object files for
# this whole directory. 

art_make( LIB_LIBRARIES canvas ${CLHEP} )

# Install header files into the products area
install_headers() 

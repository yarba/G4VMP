# Use the magic that is @art_make@ to construct the shared object files for
# this whole directory. 

# NOTE: I really have no idea what ROOT libraries are needed,
#       just figured this combination below by pocking around...
#
art_make( LIB_LIBRARIES ROOT::Core ROOT::Cling ROOT::Hist )
install_headers() 

begin
  require 'rubygems'
rescue LoadError; end
require 'ffi'

module ActiveSupport
  class FFI
    extend ::FFI::Library
    ffi_lib 'activesupport'
  end
end

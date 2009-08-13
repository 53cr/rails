begin
  require 'rubygems'
rescue LoadError; end
require 'ffi'

if !defined?(ActiveSupport::FFI)
  module ActiveSupport
    class FFI
      extend ::FFI::Library
      ffi_lib 'activesupport'
    end
  end
end

unless false # this version is faster, all around, so...
# unless '1.8.7 and up'.respond_to?(:start_with?)
  module ActiveSupport
    class FFI
      attach_function :string_starts_with, [:pointer, :pointer], :bool
      attach_function :string_ends_with,   [:pointer, :pointer], :bool
    end
  end

  class String
    def start_with?(o)
      ActiveSupport::FFI.string_starts_with(self,o)
    end
    def end_with?(o)
      ActiveSupport::FFI.string_ends_with(self,o)
    end
    
    alias_method :starts_with?, :start_with?
    alias_method :ends_with?, :end_with?
  end

end

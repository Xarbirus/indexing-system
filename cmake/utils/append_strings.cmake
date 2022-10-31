# append_strings(
#   <string_to_append>
#   <separator>
#   <strings...>)
#
# Append strings (separated by the given separator) to the given variable.
#
# --- Parameters ---
#
# string_to_append    Variable to which the given strings should be appended.
# separator           Separator used to join the given strings.
# strings             List of strings to append.

function(append_strings string_to_append separator)
  string(JOIN "${separator}" out "${${string_to_append}}" ${ARGN})
  set(${string_to_append} "${out}" PARENT_SCOPE)
endfunction()

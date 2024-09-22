# Key value database tester
# 
# @file test/key_value_test.sh
#
# @author Jacob Smith

# Feed the key value database example ...
cat input/key_value_input |

# ... into the key value database executable ...
../build/key_value_db |

# ... storing the output in the resources directory 
cat > output/key_value_output


#!/bin/bash

# Create the hooks directory if it doesn't exist
mkdir -p .git/hooks

# Set up the prepare-commit-msg hook
prepare_commit_msg_hook=".git/hooks/prepare-commit-msg"

echo "#!/bin/bash

# Available prefixes and their corresponding emojis
prefixes=(\"fix\" \"add\" \"update\" \"remove\" \"debug\")
emojis=(\"🐛\" \"🎉\" \"🔄\" \"❌\" \"🐞\")

# Extract the current commit message
commit_msg_file=\"\$1\"
commit_msg=\$(cat \"\$commit_msg_file\")

# Find the matching prefix (if any)
prefix_index=-1
for i in \${!prefixes[@]}; do
  prefix=\"\${prefixes[\$i]}\"
  if [[ \$commit_msg == \"\$prefix \"* ]]; then
    prefix_index=\"\$i\"
    break
  fi
done

# Add prefix and emoji if not already present
add_prefix() {
  local prefix=\"\$1\"
  local emoji=\"\$2\"
  local updated_commit_msg=\"\$emoji \$prefix:\"

  # Remove the prefix from the commit message
  updated_commit_msg+=\${commit_msg#\${prefix} }

  # Remove double spaces and add a space after the colon
  updated_commit_msg=\$(echo \"\$updated_commit_msg\" | sed -E 's/  +/ /g' | sed 's/:/: /')

  if [[ \$commit_msg != \"\$updated_commit_msg\"* ]]; then
    echo \"\$updated_commit_msg\" > \"\$commit_msg_file\"
  fi
}

# Determine the prefix and emoji to use
if [[ \$prefix_index -eq -1 ]]; then
  default_prefix=\"update\"
  default_emoji=\"🔄\"
else
  default_prefix=\"\${prefixes[\$prefix_index]}\"
  default_emoji=\"\${emojis[\$prefix_index]}\"
fi

# Perform prefix validation and modification
add_prefix \"\$default_prefix\" \"\$default_emoji\"
" > "$prepare_commit_msg_hook"

# Make the hook executable
chmod +x "$prepare_commit_msg_hook"

echo "Git hooks have been set up successfully."

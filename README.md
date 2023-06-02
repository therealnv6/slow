# disclaimer 
should not be used, just a project i'm working on because i'm bored.

# supports 
currently supports a couple of commands through tcp, including:

| Command | Syntax                | Description                                        |
|---------|-----------------------|----------------------------------------------------|
| get     | get \<key>            | Get the value at the key                           |
| set     | set \<key>:\<value>    | Set the value at the key                           |
| app     | app \<key>:\<value>    | Append to the value at the key                      |
| del     | del \<key>            | Delete the value at a key and remove the key       |
| len     | len                   | Get the number of keys stored in the dataset       |
| inc     | inc \<key>            | Increment the value at the key                      |
| dec     | dec \<key>            | Decrement the value at the key                      |
| exists  | exists \<key>         | Check if a value exists within the current dataset |


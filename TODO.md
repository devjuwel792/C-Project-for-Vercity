# TODO: Add Authentication System to IQ Quiz

- [x] Add sign_up() function to handle user registration, checking for existing usernames and appending to users.txt
- [x] Add log_in() function to authenticate existing users by reading users.txt and verifying credentials
- [x] Modify main() function to prompt user for Sign Up or Log In before proceeding to quiz, with retry logic (up to 3 attempts)
- [x] Update quiz flow to use authenticated username instead of manual name input
- [x] Fix string comparisons for level selection (use strcmp instead of ==)
- [ ] Compile and test the program to ensure auth works and quiz proceeds correctly

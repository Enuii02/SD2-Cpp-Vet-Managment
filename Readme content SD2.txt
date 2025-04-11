# SD2_CW

////Veterinary Management System////

//// Program intro ////

A vet management program that lets the user create accounts for staff of the vet, as well as create guest accounts for owners.

- Can create staff accounts: Admin, Vet, Staff
- Can create guest accounts for owners who would like to view their own data.

- Different staff roles have different privileges 

- Admin has access to everything and can use any part of the management system

- Vet has full access to pet management and appointment management, may only view and update owners

- Staff has full access to appointment management, may only view owners and view pets

- Guests may only view their own data 


//// How to use ////

Users will be prompted with a menu navigated through single integer inputs (menu will just loop if an invalid input is taken)

All staff accounts are stored in staffacc.txt, these follow a structure that will be created through sign up, create accounts through sign up to avoid bugs with login.

All guest/owner accounts are stored in owner.txt - they are created the same way between admin and guest. 

To create an account select sign in > select the role of the account > input the required details
- No restrictions on username and full name aside from minimum 4 characters. 

Login is straightforward, input the exact details and user will be logged in.

When adding something new (can be pet, owner, or appointment) follow the input guides for each one to avoid future bugs.

When updating it works similarly to the different add functions.

When viewing, input the according detail for individual views (e.g. pet name) unless it is viewing the whole txt file.

When deleting, input the according detail for that thing's data to be deleted.

Mateusz Skrzydlo

Owen Tsoi

Yuhang Wang
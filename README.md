# TITAN
This is the flight computer for the Domecracker liquid bi-propellant rocket. It's build with the following hardware in mind:
- **MCU**: STM32H745XIH3
- **IMU**: ICM-42688-P
- **Magnetometer**: MMC5983MA
- **Barometer**: MS561101BA03-50
- **Temperature Sensor**: TMP125AIDBVR
- **Radio**: SI4467-A2A-IMR
- **GNSS**: NEO-M8Q-01A
- **RS485 Transciever**: THVD2442DRCR

## Structure
The project has the following structure:
- *apps*: Application code. Should contain the actual startup code of the rocket, which then uses the modules.
- *dev*: Development directory. Dumping space for useful stuff that shouldn't go elsewhere.
- *modules*: Includes all subsystems for the rocket. This includes peripheral and device drivers but also the subsystems that use these drivers.
- *tests*: Where testing takes place.

Each of these directories should contain a README with more information on the directory and a current status of the directory contents.

## Contributing
### Quickstart
Go to the issues tab and use tags to filter by master-issue. Find one that you like, find or create a sub-issue for it and address it in a new branch called `work/<main-issue-branch/<issuebranch-title>`. The main issue branch will be indicated in the description of the master issue, and the the `<issuebranch-title>` should be `bug` or `feat` depending on if this issue is a bug or a feature, and then the issue title. So for a bug issue w/ the title "hello there" the `<issuebranch-title>` should be `bug-hello-there`.

Once you have addressed the issue, submit a pull request into the master issue's main branch and link it to the issue. Once it gets approved, make sure the issue is closed.

Congrats! You have made your first contribution.

### Contributing Guide
This contains a wholistic guide as to how our contribution system works.

Start by reading the READMEs of the 'modules' directory for better understanding of our project structure. Then continue below to
understand the issues and branching pipeline.

**Issues and Branching**
The issues list consists of the following **master issues**:
1. `documentation`: all issues related to documentation
2. `apps`: all issues related to app development
3. `dev`: all issues related to dev directory.
4. `modules/<module>/<module-item>`: all issues related to module-item development (see README of 'modules/')
5. `tests`: all issues related to tests.
   
All other issues should be descendants of these master issues.

TIP: Always filter the issues list by master issues and explore the tree from the top. Otherwise it is overwhelming.

All master issues recieve a **branch group**. These consist of a main branch for that issue and dev/ and bug/ branches. 
- The main branch shall be named `work/<master issue name>`
- The `dev/` and `bug/` branches shall be named `work/<master issue name>/<feat/bug>/<feature or bug name>`

`work` is just a naming prefix used to differentiat work branches from merging branches like `untested` and `main`

The idea is that when something needs to be done, that thing is described as a sub-issue within one of the master issues. Then for that issue,
a `dev/bug` branch is made, `dev` if the issue is a new feature, and `bug` if it is a bug fix. Once the coding is complete and the branch is ready
to be merged back into the master issue's main branch, a pull request is made into the main branch, which is reviewed and checked for quality before
being accepted/denied.

Then once a master issue is considered complete, it is merged through pull request into the untested branch where it is tested. Then the untested branch is
tested and merged into the main branch.

In order to maintain accountability for code quality, each master issue is assigned a supervisor.This supervisor is charged with the task of managing the task list
for the master issue (making sure all are appropriate and well formed) and accepting/denying pull requests from `dev/bug` branches into the main branch of the master issue. 

Each master branch has checklist designed to enforce minimum requirements to passing code, which is added as the first comment of the issue.

Each pull request approval/denial must:
1. Address all items in the checklist
2. Summarize decision and reason for decision

If a new supervisor is chosen, upper-level management will oversee all pull request decisions made by the supervisor until 5 errorless pull request decisions have been made by the supervisor.

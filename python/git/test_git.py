import os
import subprocess as subp
import tempfile

# Temporary git repository path
TEMP_GIT_REPO_PATH = os.path.join(tempfile.gettempdir(), "scriptrepository_unittest")
# Temporary git repository path
TEMP_GIT_REMOTE_PATH = os.path.join(tempfile.gettempdir(), "scriptrepository_unittest_remote")

def _setup_test_git_repos():
    os.mkdir(TEMP_GIT_REMOTE_PATH)
    start_dir = os.getcwd()

    # Init the remote
    os.chdir(TEMP_GIT_REMOTE_PATH)
    subp.check_output("git init", stderr=subp.STDOUT, shell=True)
    # Create a commit so we can use reset
    readme = os.path.join(TEMP_GIT_REMOTE_PATH, "README.md")
    open(readme, 'w').write("foo")
    subp.check_output("git add .; git commit -m'Initial commit';exit 0",
                            stderr=subp.STDOUT, shell=True)
    # Chcekout out to some commit directly so that pushing to master is allowed
    sha1 = subp.check_output("git rev-parse HEAD;exit 0",
                            stderr=subp.STDOUT, shell=True)
    FIRST_COMMIT = sha1.rstrip()
    subp.check_output("git checkout {0};exit 0".format(FIRST_COMMIT),
                            stderr=subp.STDOUT, shell=True)
    # Clone this so that the clone will have a remote
    os.chdir(os.path.dirname(TEMP_GIT_REPO_PATH))
    cmd = "git clone {0} {1}; exit 0".format(TEMP_GIT_REMOTE_PATH, TEMP_GIT_REPO_PATH)
    subp.check_output(cmd, stderr=subp.STDOUT, shell=True)

    # Go back to where we started
    os.chdir(start_dir)

def _git(cmd, args):
    args.insert(0, cmd)
    return _shellcmd("git", args)

#-------------------------------------------------------------------------------
def _shellcmd(cmd, args=[]):
    """Use subprocess to call a given command.
    Return stdout/stderr if an error occurred
    """
    cmd = [cmd]
    cmd.extend(args)
    print cmd
    try:
        p = subp.Popen(cmd, stdout=subp.PIPE, stderr=subp.PIPE)
    except ValueError, err:
        raise RuntimeError(err)
    stdout, stderr = p.communicate()
    if p.returncode == 0:
        return stdout
    else:
        raise RuntimeError(stdout + stderr)

def add(filelist):
    _git("add", filelist)

def commit(author, email, committer, msg):
    """Commits all of the changes detailed by the CommitInfo object"""
    author = '--author="{0} <{1}>"'.format(author, email)
    msg = '-m {0}'.format(msg)

    # Only way to reset the committer without
    os.environ['GIT_COMMITTER_NAME'] = committer
    _git('commit',[author, msg])
    del os.environ["GIT_COMMITTER_NAME"]

# ----------------------------------------------------------------------------

_setup_test_git_repos()
os.chdir(TEMP_GIT_REPO_PATH)
repo_file = os.path.join(TEMP_GIT_REPO_PATH, "muon", "userscript.py")
os.mkdir(os.path.dirname(repo_file))
open(repo_file, 'w').write("foo")
add([repo_file])
#commit("Martyn Gigg", "j.bloggs@domain.com", "mantid-publisher", "A no quotes message")
comment = "A \"quoted\" message"
commit("Martyn \"Gigg", "j.\"bloggs@domain.com", "mantid-publisher", comment)

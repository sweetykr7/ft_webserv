export BREWDIR="$HOME/goinfre/homebrew"

rm -rf "$BREWDIR"
rm -rf "$HOME/goinfre/Applications"

mkdir -p "$HOME/goinfre/Applications"
ln -s "$HOME/goinfre/Applications" "$HOME/Applications"
git clone https://github.com/Homebrew/brew $BREWDIR

$BREWDIR/bin/brew shellenv >> $HOME/.zshrc
echo 'export HOMEBREW_CASK_OPTS="--appdir=$HOME/goinfre/Applications"' >> $HOME/.zshrc
source $HOME/.zshrc

brew install cmake

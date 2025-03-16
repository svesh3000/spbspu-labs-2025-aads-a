#include "postfix-utils.h"
#include <stack>
#include "postfix-expression.h"

void savintsev::io_postfix_results(std::istream & in)
{
  using namespace std;

  string text;
  stack< long long > results;

  while (in)
  {
    getline(in, text);
    if (text.empty())
    {
      continue;
    }

    PostfixExpr expr = convert(text);
    results.push(expr());
  }

  if (results.empty())
  {
    cout << '\n';
    return;
  }

  cout << results.top();
  results.pop();

  while (!results.empty())
  {
    cout << " " << results.top();
    results.pop();
  }

  cout << '\n';
}

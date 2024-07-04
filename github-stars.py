import requests

def get_all_stargazers(owner, repo):
    stargazers = []
    page = 1
    per_page = 100  # 每页最多可以获取100个stargazers

    while True:
        url = f"https://api.github.com/repos/{owner}/{repo}/stargazers"
        params = {
            "page": page,
            "per_page": per_page
        }
        headers = {
            "Accept": "application/vnd.github.v3+json"
        }
        response = requests.get(url, headers=headers, params=params)

        if response.status_code != 200:
            print(f"Failed to fetch stargazers: {response.status_code}")
            break

        page_stargazers = response.json()
        if not page_stargazers:
            break  # No more stargazers

        stargazers.extend(page_stargazers)
        page += 1

    return stargazers

owner = "wmacro"
repo = "codes"
stargazers = get_all_stargazers(owner, repo)

stargazers_names = []

if stargazers:
    for user in stargazers:
        stargazers_names.append(user['login'])
    print(len(stargazers_names))
    print(stargazers_names)
else:
    print("No stargazers found or failed to fetch stargazers.")

/*
 * @lc app=leetcode id=355 lang=cpp
 *
 * [355] Design Twitter
 *
 * https://leetcode.com/problems/design-twitter/description/
 *
 * algorithms
 * Medium (28.51%)
 * Total Accepted:    40.7K
 * Total Submissions: 142.6K
 * Testcase Example:  '["Twitter","postTweet","getNewsFeed","follow","postTweet","getNewsFeed","unfollow","getNewsFeed"]\n' +
  '[[],[1,5],[1],[1,2],[2,6],[1],[1,2],[1]]'
 *
 * Design a simplified version of Twitter where users can post tweets,
 * follow/unfollow another user and is able to see the 10 most recent tweets in
 * the user's news feed. Your design should support the following methods:
 *
 *
 *
 * postTweet(userId, tweetId): Compose a new tweet.
 * getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's
 * news feed. Each item in the news feed must be posted by users who the user
 * followed or by the user herself. Tweets must be ordered from most recent to
 * least recent.
 * follow(followerId, followeeId): Follower follows a followee.
 * unfollow(followerId, followeeId): Follower unfollows a followee.
 *
 *
 *
 * Example:
 *
 * Twitter twitter = new Twitter();
 *
 * // User 1 posts a new tweet (id = 5).
 * twitter.postTweet(1, 5);
 *
 * // User 1's news feed should return a list with 1 tweet id -> [5].
 * twitter.getNewsFeed(1);
 *
 * // User 1 follows user 2.
 * twitter.follow(1, 2);
 *
 * // User 2 posts a new tweet (id = 6).
 * twitter.postTweet(2, 6);
 *
 * // User 1's news feed should return a list with 2 tweet ids -> [6, 5].
 * // Tweet id 6 should precede tweet id 5 because it is posted after tweet id
 * 5.
 * twitter.getNewsFeed(1);
 *
 * // User 1 unfollows user 2.
 * twitter.unfollow(1, 2);
 *
 * // User 1's news feed should return a list with 1 tweet id -> [5],
 * // since user 1 is no longer following user 2.
 * twitter.getNewsFeed(1);
 *
 *
 */

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Twitter {
  private:
    static int timestamp_;

    struct Tweet {
        int id_;
        int time_;
        Tweet *next_;

        Tweet(int id, int time) : id_(id), time_(time), next_(nullptr) {}
    };

    struct User {
        int id_;
        unordered_set<int> followees_;
        Tweet *head_;

        User(int id) : id_(id), head_(nullptr) {
            follow(id);
        }

        void follow(int followeeId) {
            followees_.insert(followeeId);
        }

        void unfollow(int followeeId) {
            // can't unfollow yourself
            if (followeeId == id_) return;
            followees_.erase(followeeId);
        }

        void post(int tweetId) {
            Tweet *tweet = new Tweet(tweetId, timestamp_++);
            tweet->next_ = head_;
            head_ = tweet;
        }
    };

    unordered_map<int, User *> userMap;

  public:
    /** Initialize your data structure here. */
    Twitter() {
        timestamp_ = 0;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        // make sure user exist
        if (userMap.find(userId) == userMap.end())
            userMap[userId] = new User(userId);
        userMap[userId]->post(tweetId);
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> res;
        // no such user, return no result
        if (userMap.find(userId) == userMap.end()) return res;
        auto comp = [](Tweet *a, Tweet *b) {
            return a->time_ < b->time_;
        };
        priority_queue<Tweet *, vector<Tweet *>, decltype(comp)> tweetHeap(comp);
        for (int id : userMap[userId]->followees_) {
            Tweet *twt = userMap[id]->head_;
            if (twt != nullptr)
                tweetHeap.push(twt);
        }

        while (!tweetHeap.empty()) {
            Tweet *twt = tweetHeap.top();
            tweetHeap.pop();
            res.push_back(twt->id_);
            if (twt->next_ != nullptr)
                tweetHeap.push(twt->next_);
            if (res.size() == 10) break;
        }

        return res;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        // make sure followee exist
        if (userMap.find(followeeId) == userMap.end())
            userMap[followeeId] = new User(followeeId);
        // make sure follower exist
        if (userMap.find(followerId) == userMap.end())
            userMap[followerId] = new User(followerId);
        // follow
        userMap[followerId]->follow(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if (userMap.find(followerId) != userMap.end())
            userMap[followerId]->unfollow(followeeId);
    }
};

int Twitter::timestamp_ = 0;

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

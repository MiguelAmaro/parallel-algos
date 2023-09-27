import gymnasium as gym

print("running gym test")

env = gym.make("CartPole-v1", render_mode="rgb_array")

observation, info = env.reset(seed=42)
for _ in range(1000):
    action = env.action_space.sample()
    observation, reward, terminated, truncated, info = env.step(action)

    if terminated or truncated:
        observation, info = env.reset()
    env.render()


env.close()
print("finished gym test")
